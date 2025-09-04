#include "graphic/Fast3D/interpreter.h"

static Fast::Interpreter gfx;

extern "C" {

  void gfx_init() {

    Fast::GfxWindowBackendDXGI wapi;
    Fast::GfxRenderingAPIDX11 rapi;

    gfx.Init(&wapi,&rapi,"Banjo Kazooie PC", false, 480,640,0,0);
  }

  void gfx_set_fps(int fps) {
    gfx.SetTargetFPS(fps);
  }

  void gfx_start_frame() {
      gfx.StartFrame();
  }

 // void gfx_run(*Gfx cmds) {
  //    gfx.Run(cmds,{});
  //}

  void gfx_end_frame() {
    gfx.EndFrame();
  }

}