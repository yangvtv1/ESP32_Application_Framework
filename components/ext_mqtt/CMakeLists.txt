idf_component_register(
    SRCS "ext_mqtt.c"
    INCLUDE_DIRS "."
    REQUIRES ext_mqtt mqtt esp_event ext_ntp EMBED_TXTFILES tuya_root.pem
)