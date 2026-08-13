#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>

/* ================= MPU6050 REGISTERS ================= */
#define MPU_ADDR        0x68
#define PWR_MGMT_1      0x6B
#define ACCEL_XOUT_H    0x3B
#define ACCEL_YOUT_H    0x3D
#define ACCEL_ZOUT_H    0x3F
#define GYRO_XOUT_H     0x43
#define GYRO_YOUT_H     0x45
#define GYRO_ZOUT_H     0x47

/* ================= ESP32-C3 PINS ================= */
#define SDA_PIN        4
#define SCL_PIN        5
#define RED_LED_PIN    8
#define RESET_BTN_PIN  9

/* ================= SENSOR SCALE ================= */
const float ACC_SENS  = 16384.0;
const float GYRO_SENS = 131.0;

/* ================= FILTER & LIMITS ================= */
const float ALPHA = 0.98;
const float MAX_KNEE_ANGLE = 140.0;

/* ================= WIFI ================= */
const char* AP_SSID = "Knee-Rehab";
const char* AP_PASS = "rehab123";

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

/* ================= STATE ================= */
float kneeAngle = 0.0;
float maxFlexion = 0.0;
bool compensation = false;
bool movementQualityGood = true;

float zeroOffset = 0.0;
bool calibrated = false;

unsigned long lastTime = 0;
unsigned long compStartTime = 0;

/* ===== REP STATE MACHINE ===== */
int repCount = 0;
int phase = 0;  // 0=REST,1=FLEXING,2=EXTENDING

const float START_THRESHOLD = 20.0;
const float PEAK_THRESHOLD  = 60.0;

float lastAngle = 0.0;
bool reachedPeak = false;

/* ================= RESET SESSION ================= */
void resetSession()
{
  kneeAngle = 0;
  maxFlexion = 0;
  repCount = 0;
  phase = 0;
  reachedPeak = false;
  calibrated = false;
  zeroOffset = 0;
}

/* ================= I2C ================= */
int16_t read16(uint8_t reg)
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 2, true);
  return (Wire.read() << 8) | Wire.read();
}

void readAccel(float &ax, float &ay, float &az)
{
  ax = read16(ACCEL_XOUT_H) / ACC_SENS;
  ay = read16(ACCEL_YOUT_H) / ACC_SENS;
  az = read16(ACCEL_ZOUT_H) / ACC_SENS;
}

void readGyro(float &gx, float &gy, float &gz)
{
  gx = read16(GYRO_XOUT_H) / GYRO_SENS;
  gy = read16(GYRO_YOUT_H) / GYRO_SENS;
  gz = read16(GYRO_ZOUT_H) / GYRO_SENS;
}

/* ================= MOTION UPDATE ================= */
void updateMotion()
{
  float ax, ay, az;
  float gx, gy, gz;

  readAccel(ax, ay, az);
  readGyro(gx, gy, gz);

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;
  if (dt <= 0) return;

  /* ===== Angle Calculation ===== */
  float accAngle = atan2(ay, az) * 180.0 / PI;
  float gyroPrediction = kneeAngle + gy * dt;
  kneeAngle = ALPHA * gyroPrediction + (1.0 - ALPHA) * accAngle;

  /* ===== Stable Calibration ===== */
  static int stableCount = 0;

  if (!calibrated)
  {
    if (abs(gx) < 5 && abs(gy) < 5 && abs(gz) < 5)
    {
      stableCount++;
      if (stableCount > 50)
      {
        zeroOffset = kneeAngle;
        calibrated = true;
      }
    }
    else stableCount = 0;
  }

  /* ===== Reverse Direction Properly ===== */
  kneeAngle = -(kneeAngle - zeroOffset);

  if (kneeAngle < 0) kneeAngle = 0;
  if (kneeAngle > MAX_KNEE_ANGLE) kneeAngle = MAX_KNEE_ANGLE;

  if (kneeAngle > maxFlexion)
    maxFlexion = kneeAngle;

  /* ===== Improved Movement Quality ===== */
  float stabilityIndex = abs(gx) + abs(gz);

  if (stabilityIndex > 40)
  {
    if (compStartTime == 0)
      compStartTime = millis();

    if (millis() - compStartTime > 200)
    {
      compensation = true;
      movementQualityGood = false;
      digitalWrite(RED_LED_PIN, HIGH);
    }
  }
  else
  {
    compStartTime = 0;
    compensation = false;
    movementQualityGood = true;
    digitalWrite(RED_LED_PIN, LOW);
  }

  /* ===== REP DETECTION ===== */
  float velocity = kneeAngle - lastAngle;

  switch (phase)
  {
    case 0:
      if (kneeAngle > START_THRESHOLD && velocity > 0)
      {
        phase = 1;
        reachedPeak = false;
      }
      break;

    case 1:
      if (kneeAngle > PEAK_THRESHOLD)
        reachedPeak = true;

      if (velocity < 0)
        phase = 2;
      break;

    case 2:
      if (kneeAngle < START_THRESHOLD)
      {
        if (reachedPeak)
          repCount++;
        phase = 0;
      }
      break;
  }

  lastAngle = kneeAngle;
}

/* ================= API ================= */
void handleData()
{
  updateMotion();

  float extDeg = maxFlexion - kneeAngle;
  if (extDeg < 0) extDeg = 0;

  String json = "{";
  json += "\"angle\":" + String(kneeAngle,1) + ",";
  json += "\"max\":"   + String(maxFlexion,1) + ",";
  json += "\"ext\":"   + String(extDeg,1) + ",";
  json += "\"reps\":"  + String(repCount) + ",";
  json += "\"warn\":"  + String(compensation ? "true" : "false");
  json += "}";

  server.send(200, "application/json", json);
}

void handleReset()
{
  resetSession();
  server.send(200, "text/plain", "Reset Done");
}

/* ================= WEB UI ================= */
void handleRoot()
{
  server.send(200, "text/html",
  "<!DOCTYPE html>"
  "<html lang='en'>"
  "<head>"
  "<meta charset='UTF-8'>"
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
  "<title>Knee Rehabilitation Monitor</title>"

  "<style>"
  "body{margin:0;font-family:Arial;background:linear-gradient(135deg,#e0f2fe,#f8fafc);color:#0f172a;}"
  "h1{font-size:24px;font-weight:800;text-align:center;margin:20px 0;}"
  ".container{max-width:420px;margin:auto;padding:16px;}"
  ".card{background:rgba(255,255,255,0.9);border-radius:18px;padding:18px;margin-bottom:16px;"
  "box-shadow:0 8px 25px rgba(0,0,0,0.08);transition:0.2s;}"
  ".card:hover{transform:translateY(-4px);}"
  ".label{font-size:13px;color:#64748b;margin-bottom:6px;}"
  ".value{font-size:38px;font-weight:800;}"
  ".row{display:flex;gap:12px;}"
  ".half{flex:1;}"
  ".status-ok{color:#047857;font-weight:800;}"
  ".status-warn{color:#b91c1c;font-weight:800;animation:pulse 1s infinite;}"
  "@keyframes pulse{0%{opacity:1;}50%{opacity:0.5;}100%{opacity:1;}}"
  ".bar-bg{width:100%;height:16px;background:#e2e8f0;border-radius:12px;overflow:hidden;margin-top:12px;}"
  ".bar-fill{height:100%;width:0%;background:linear-gradient(90deg,#2563eb,#3b82f6);transition:width 0.25s ease;}"
  ".footer{text-align:center;font-size:12px;color:#64748b;margin-top:20px;}"
  "button{width:100%;padding:12px;border:none;border-radius:10px;"
  "background:#2563eb;color:white;font-weight:600;font-size:14px;cursor:pointer;}"
  "button:hover{background:#1d4ed8;}"
  "</style>"
  "</head>"

  "<body>"
  "<h1>Knee Rehabilitation Monitor</h1>"

  "<div class='container'>"

  "<div class='card'>"
    "<div class='label'>Current Knee Angle</div>"
    "<div class='value'><span id='angle'>0</span>°</div>"
    "<div class='bar-bg'><div id='angleBar' class='bar-fill'></div></div>"
  "</div>"

  "<div class='row'>"
    "<div class='card half'>"
      "<div class='label'>Maximum Flexion</div>"
      "<div class='value'><span id='max'>0</span>°</div>"
    "</div>"
    "<div class='card half'>"
      "<div class='label'>Extension</div>"
      "<div class='value'><span id='ext'>0</span>°</div>"
    "</div>"
  "</div>"

  "<div class='card'>"
    "<div class='label'>Total Repetitions</div>"
    "<div class='value'><span id='reps'>0</span></div>"
  "</div>"

  "<div class='card'>"
    "<div class='label'>Movement Quality</div>"
    "<div class='value'><span id='status' class='status-ok'>GOOD</span></div>"
  "</div>"

  "<div class='card'>"
    "<button onclick='resetSession()'>Reset Session</button>"
  "</div>"

  "<div class='footer'>Rehabilitation Monitoring Prototype</div>"
  "</div>"

  "<script>"
  "function resetSession(){fetch('/reset');}"

  "setInterval(async ()=>{"
    "try{"
      "let r = await fetch('/data');"
      "let d = await r.json();"

      "angle.innerText = d.angle.toFixed(1);"
      "max.innerText   = d.max.toFixed(1);"
      "ext.innerText   = d.ext.toFixed(1);"
      "reps.innerText  = d.reps;"

      "let pct = Math.min((d.angle / 140) * 100, 100);"
      "angleBar.style.width = pct + '%';"

      "if(d.warn){"
        "status.innerText = 'COMPENSATION';"
        "status.className = 'status-warn';"
        "angleBar.style.background = '#f59e0b';"
      "}else{"
        "status.innerText = 'GOOD';"
        "status.className = 'status-ok';"
        "angleBar.style.background = 'linear-gradient(90deg,#2563eb,#3b82f6)';"
      "}"
    "}catch(e){}"
  "},300);"
  "</script>"

  "</body>"
  "</html>"
  );
}
/* ================= SETUP ================= */
void setup()
{
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(RESET_BTN_PIN, INPUT_PULLUP);
  digitalWrite(RED_LED_PIN, LOW);

  Wire.begin(SDA_PIN, SCL_PIN);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x00);
  Wire.endTransmission();

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.on("/reset", handleReset);

  server.begin();
  lastTime = millis();
}

/* ================= LOOP ================= */
void loop()
{
  server.handleClient();

  if (digitalRead(RESET_BTN_PIN) == LOW)
  {
    delay(200);
    ESP.restart();
  }
}
