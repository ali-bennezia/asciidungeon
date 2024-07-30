#ifndef _UI_H_
#define _UI_H_

enum ASCIIDNG_UI_INSTANCE_TYPE {
	ASCIIDNG_UI_TEXT,
	ASCIIDNG_UI_FRAME,
	ASCIIDNG_UI_IMAGE,
	ASCIIDNG_UI_BUTTON,
};

struct UIText;
typedef struct UIText UIText;
struct UIFrame;
typedef struct UIFrame UIFrame;
struct UIImage;
typedef struct UIImage UIImage;

struct _MouseEvent;
typedef struct _MouseEvent MouseEvent;

typedef void (*UICallback)(MouseEvent, void *ui_instance, enum ASCIIDNG_UI_INSTANCE_TYPE);

typedef struct UICallbacks {
	UICallback on_mouse_click_callback;
	UICallback on_mouse_enter_callback;
	UICallback on_mouse_leave_callback;
} UICallbacks;

typedef struct UITextInstance {
	UIText *ui_txt;
	UICallbacks callbacks;
} UITextInstance;
typedef struct UIFrameInstance {
	UIFrame *ui_frame;
	UICallbacks callbacks;
} UIFrameInstance;
typedef struct UIImageInstance {
	UIImage *ui_image;
	UICallbacks callbacks;
} UIImageInstance;
typedef struct UIButtonInstance {
	UIText *ui_txt;
	UIFrame *ui_frame;
	UICallbacks callbacks;
} UIButtonInstance;

void asciidng_init_ui();
void asciidng_terminate_ui();

#endif
