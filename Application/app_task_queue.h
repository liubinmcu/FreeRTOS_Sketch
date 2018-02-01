#ifndef __APP_TASK_QUEUE_H
#define __APP_TASK_QUEUE_H

#include "global_include.h"


void vTaskQueueStart( void* pvParameters );

extern QueueHandle_t xHandleQueueMsg;

#endif /* __APP_TASK_QUEUE_H */
