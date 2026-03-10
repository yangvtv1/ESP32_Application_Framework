idf_component_register(
    SRCS "ext_gpio.c"
    INCLUDE_DIRS "."
    REQUIRES ext_mqtt mqtt esp_event
)