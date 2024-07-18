#ifndef _UI_H_
#define _UI_H_

struct UIText;
typedef struct UIText UIText;
struct UIFrame;
typedef struct UIFrame UIFrame;
struct UIImage;
typedef struct UIImage UIImage;

typedef struct UITextInstance {
	UIText *ui_txt;
} UITextInstance;
typedef struct UIFrameInstance {
	UIFrame *ui_frame;
} UIFrameInstance;
typedef struct UIImageInstance {
	UIImage *ui_image;
} UIImageInstance;
typedef struct UIButtonInstance {
	UIText *ui_txt;
	UIFrame *ui_frame;
} UIButtonInstance;

void asciidng_init_ui();
void asciidng_terminate_ui();

#endif
