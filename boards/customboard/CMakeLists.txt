

zephyr_sources_ifdef(CONFIG_NRF_TIMER_TIMER nrf_timer_timer.c)
zephyr_library()
zephyr_library_sources(board.c)