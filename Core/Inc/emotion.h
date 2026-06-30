#ifndef _EMOTION_H
#define _EMOTION_H

typedef enum {
    PetState_Awake = 0, // 醒着
    PetState_Asleep,    // 睡着
    PetState_Count
} PetStateDef;

// 2. 定义微观情绪状态 (Sub State - 仅在 Awake 状态下有效)
typedef enum {
    Emotion_Normal = 0,
    Emotion_Happy,
    Emotion_Alert,
    Emotion_Angry,
    Emotion_Curious,
    Emotion_Shy,
    Emotion_Count 
} EmotionTypeDef

#endif 