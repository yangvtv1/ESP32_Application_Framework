idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES ext_mqtt ext_wifi ext_gpio ext_ntp
)