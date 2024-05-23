idf_component_register(SRCS "Master_spi.c"
                    INCLUDE_DIRS "."
                    INCLUDE_DIRS "include"
                    REQUIRES "driver"
                    REQUIRES "esp_system"
                    REQUIRES "esp_event"
                    REQUIRES "nvs_flash"
                    REQUIRES "esp_timer"
                    )
                    list(APPEND EXTRA_COMPONENT_DIRS components)
