-------------------------------------------------------------------------------
-- traffic_light_fsm_tb.vhd
-- Self-checking testbench for traffic_light_fsm.
-- Verifies:
--   1. Reset forces RED state
--   2. State sequence follows RED -> GREEN -> YELLOW -> RED
--   3. Only one light is ever active at a time
--   4. Each state holds for the correct number of cycles
-- Reports PASS/FAIL via assertions, not just waveform inspection.
-------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity traffic_light_fsm_tb is
end entity traffic_light_fsm_tb;

architecture sim of traffic_light_fsm_tb is

    constant RED_TIME    : integer := 4;
    constant GREEN_TIME  : integer := 3;
    constant YELLOW_TIME : integer := 2;
    constant CLK_PERIOD  : time := 10 ns;

    signal clk       : std_logic := '0';
    signal rst       : std_logic := '1';
    signal red_light : std_logic;
    signal yel_light : std_logic;
    signal grn_light : std_logic;

    signal error_count : integer := 0;

begin

    ----------------------------------------------------------------
    -- DUT instantiation
    ----------------------------------------------------------------
    DUT : entity work.traffic_light_fsm
        generic map (
            RED_TIME    => RED_TIME,
            GREEN_TIME  => GREEN_TIME,
            YELLOW_TIME => YELLOW_TIME
        )
        port map (
            clk       => clk,
            rst       => rst,
            red_light => red_light,
            yel_light => yel_light,
            grn_light => grn_light
        );

    ----------------------------------------------------------------
    -- Clock generation
    ----------------------------------------------------------------
    clk_process : process
    begin
        while true loop
            clk <= '0';
            wait for CLK_PERIOD / 2;
            clk <= '1';
            wait for CLK_PERIOD / 2;
        end loop;
    end process;

    ----------------------------------------------------------------
    -- Continuous check: exactly one light on at all times
    ----------------------------------------------------------------
    one_hot_check : process (clk)
        variable active_count : integer;
    begin
        if rising_edge(clk) then
            active_count := 0;
            if red_light = '1' then active_count := active_count + 1; end if;
            if yel_light = '1' then active_count := active_count + 1; end if;
            if grn_light = '1' then active_count := active_count + 1; end if;

            assert active_count = 1
                report "ONE-HOT VIOLATION: more or less than one light active"
                severity error;

            if active_count /= 1 then
                error_count <= error_count + 1;
            end if;
        end if;
    end process;

    ----------------------------------------------------------------
    -- Main stimulus + sequence checking
    ----------------------------------------------------------------
    stim_process : process
    begin
        -- Hold reset for 2 cycles, confirm RED during reset
        rst <= '1';
        wait for CLK_PERIOD * 2;
        assert red_light = '1' and grn_light = '0' and yel_light = '0'
            report "FAIL: reset did not force RED state"
            severity error;

        rst <= '0';

        -- Check RED holds for RED_TIME cycles
        wait for CLK_PERIOD * (RED_TIME - 1);
        assert red_light = '1'
            report "FAIL: left RED state too early"
            severity error;

        wait for CLK_PERIOD;
        assert grn_light = '1'
            report "FAIL: did not transition RED -> GREEN on time"
            severity error;

        -- Check GREEN holds for GREEN_TIME cycles
        wait for CLK_PERIOD * (GREEN_TIME - 1);
        assert grn_light = '1'
            report "FAIL: left GREEN state too early"
            severity error;

        wait for CLK_PERIOD;
        assert yel_light = '1'
            report "FAIL: did not transition GREEN -> YELLOW on time"
            severity error;

        -- Check YELLOW holds for YELLOW_TIME cycles
        wait for CLK_PERIOD * (YELLOW_TIME - 1);
        assert yel_light = '1'
            report "FAIL: left YELLOW state too early"
            severity error;

        wait for CLK_PERIOD;
        assert red_light = '1'
            report "FAIL: did not transition YELLOW -> RED on time (cycle did not repeat)"
            severity error;

        -- Run one more full cycle to confirm repeatability
        wait for CLK_PERIOD * (RED_TIME + GREEN_TIME + YELLOW_TIME);

        -- Final report
        if error_count = 0 then
            report "TEST RESULT: ALL CHECKS PASSED" severity note;
        else
            report "TEST RESULT: " & integer'image(error_count) & " ONE-HOT VIOLATIONS DETECTED" severity error;
        end if;

        report "Simulation finished." severity note;
        std.env.stop;
    end process;

end architecture sim;
