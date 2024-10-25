include $(TOPDIR)/rules.mk

PKG_NAME:=IoT_Memory_Reporter
PKG_RELEASE:=1
PKG_VERSION:=1.0.0
PKG_BUILD_DEPENDS:=!USE_GLIBC:argp-standalone

include $(INCLUDE_DIR)/package.mk

define Package/IoT_Memory_Reporter
	CATEGORY:=Base system
	TITLE:=IoT_Memory_Reporter
	DEPENDS:=+libjson-c +libtuya +libubus +libubox +libblobmsg-json
endef

define Package/IoT_Memory_Reporter/description
	Daemon application for communicating with Tuya IoT Cloud with through RutOS OpenWRT system.
endef

ifndef CONFIG_USE_GLIBC
	CONFIGURE_VARS += LIBS="-largp"
endif

define Package/IoT_Memory_Reporter/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/IoT_Memory_Reporter $(1)/usr/bin
	$(INSTALL_BIN) ./files/iot_mem.init $(1)/etc/init.d/iot_mem
	$(INSTALL_CONF) ./files/iot_mem.config $(1)/etc/config/iot_mem
endef

$(eval $(call BuildPackage,IoT_Memory_Reporter))