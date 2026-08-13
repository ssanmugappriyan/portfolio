-------------------------------------------------------------------------------
-- traffic_light_fsm.vhd
-- Moore FSM traffic light controller: RED -> GREEN -> YELLOW -> RED
-- Timing (in clock cycles, generics so testbench can use small values):
--   RED    : RED_TIME cycles
--   GREEN  : GREEN_TIME cycles
--   YELLOW : YELLOW_TIME cycles
-------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity traffic_light_fsm is
    generic (
        RED_TIME    : integer := 4;
        GREEN_TIME  : integer := 3;
        YELLOW_TIME : integer := 2
    );
    port (
        clk        : in  std_logic;
        rst        : in  std_logic;                     -- synchronous, active-high
        red_light  : out std_logic;
        yel_light  : out std_logic;
        grn_light  : out std_logic
    );
end entity traffic_light_fsm;

architecture rtl of traffic_light_fsm is

    type state_t is (RED, GREEN, YELLOW);
    signal state, next_state : state_t;

    -- counts how long we've been in the current state
    signal count, next_count : integer range 0 to RED_TIME;

begin

    -- Sequential process: state + counter register
    process (clk)
    begin
        if rising_edge(clk) then
            if rst = '1' then
                state <= RED;
                count <= 0;
            else
                state <= next_state;
                count <= next_count;
            end if;
        end if;
    end process;

    -- Combinational process: next-state and counter logic
    process (state, count)
    begin
        next_state <= state;
        next_count <= count + 1;

        case state is
            when RED =>
                if count >= RED_TIME - 1 then
                    next_state <= GREEN;
                    next_count <= 0;
                end if;

            when GREEN =>
                if count >= GREEN_TIME - 1 then
                    next_state <= YELLOW;
                    next_count <= 0;
                end if;

            when YELLOW =>
                if count >= YELLOW_TIME - 1 then
                    next_state <= RED;
                    next_count <= 0;
                end if;
        end case;
    end process;

    -- Moore outputs: depend only on current state
    red_light <= '1' when state = RED   else '0';
    grn_light <= '1' when state = GREEN else '0';
    yel_light <= '1' when state = YELLOW else '0';

end architecture rtl;
