idf_component_register(
    SRCS "ext_ntp.c"
    INCLUDE_DIRS "."
    REQUIRES ext_mqtt mqtt esp_event
)