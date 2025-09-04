#ifdef __cplusplus
extern "C" {
#endif

void gfx_init();
void gfx_set_fps(int fps);
void gfx_run_frame(void* cmds);

#ifdef __cplusplus
}
#endif