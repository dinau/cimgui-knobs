all:
	$(MAKE) -C demo/c
	$(MAKE) -C demo/cpp

.PHONY: clean

clean:
	@-$(MAKE) -C demo/c   clean
	@-$(MAKE) -C demo/cpp clean

CIMGUI_ORG_DIR = ../cimgui
gen:
	-rm -fr libs/cimgui
	-mkdir -p libs/cimgui/imgui/backends
	-cp  $(CIMGUI_ORG_DIR)/{cimgui*.*,LICENSE,*.md,Makefile}            libs/cimgui/
	-cp  $(CIMGUI_ORG_DIR)/imgui/*.*                                    libs/cimgui/imgui/
	-cp  $(CIMGUI_ORG_DIR)/imgui/backends/imgui_impl_{glfw.*,opengl3*}  libs/cimgui/imgui/backends/
