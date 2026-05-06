#include "oled.h"
#include <string.h>
#include <oled_frames.c>
#include <animation.h>

//建表
extern const uint8_t oled_happy_0[OLED_BUFFER_SIZE];
extern const uint8_t oled_happy_1[OLED_BUFFER_SIZE];
//......
extern const uint8_t oled_normal_0[OLED_BUFFER_SIZE];
extern const uint8_t oled_normal_1[OLED_BUFFER_SIZE];
//......
extern const uint8_t oled_fear_0[OLED_BUFFER_SIZE];
extern const uint8_t oled_fear_1[OLED_BUFFER_SIZE];
//......
static const uint8_t *happy_frames[] = {oled_happy_0, oled_happy_1};
static const uint8_t *normal_frames[] = {oled_normal_0, oled_normal_1};
static const uint8_t *fear_frames[] = {oled_fear_0, oled_fear_1};

static const AnimationTypedef
emotion_animation_table[] = {
    [Emotion_Happy] = {
        .frame_list = happy_frames,
        .frame_count = 3
    },
    [Emotion_Normal] = {
        .frame_list = normal_frames,
        .frame_count = 3
    },
    [Emotion_Fear] = {
        .frame_list = fear_frames,
        .frame_count = 3
    }
}
//切换逻辑
//同状态循环播放 换状态播放完上一状态后切换到新状态

OledCurrentStateTypedef current_state = {
    .current_emotion = Emotion_Normal,
    .previous_emotion = Emotion_Normal,
    .frame_count = 0
};

void animation_update(OledTypedef *oled) {
    if(current_state.current_emotion != current_state.previous_emotion && current_state.frame_count >= emotion_animation_table[current_state.previous_emotion].frame_count) {
        current_state.frame_count = 0;
        current_state.previous_emotion = current_state.current_emotion;
    }

    const AnimationTypedef *animation = &emotion_animation_table[current_state.current_emotion];
    const uint8_t *frame = animation->frame_list[current_state.frame_count % animation->frame_count];
    oled_show_frame(oled, frame);
    current_state.frame_count++;
}