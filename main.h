#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Project configuration
#define PROJECT_NAME "CI_CD_Embedded"
#define PROJECT_VERSION "1.0.0"
#define AUTHOR "Selbakai"
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__

// Hardware simulation constants
#define MAX_SENSORS 4
#define BUFFER_SIZE 256
#define GPIO_PINS 16

// Error codes
typedef enum {
  SUCCESS = 0,
  ERROR_INIT = -1,
  ERROR_SENSOR = -2,
  ERROR_MEMORY = -3,
  ERROR_GPIO = -4
} error_code_t;

// GPIO pin states
typedef enum { GPIO_LOW = 0, GPIO_HIGH = 1 } gpio_state_t;

// Sensor data structure
typedef struct {
  uint8_t id;
  uint16_t value;
  uint32_t timestamp;
  uint8_t status;
} sensor_data_t;

// System information structure
typedef struct {
  char name[32];
  char version[16];
  char author[32];
  uint32_t uptime;
  uint8_t gpio_states[GPIO_PINS];
  sensor_data_t sensors[MAX_SENSORS];
} system_info_t;

// Function declarations
void display_project_info(void);
void display_build_info(void);
error_code_t init_system(void);
error_code_t init_gpio(void);
error_code_t init_sensors(void);
void gpio_write(uint8_t pin, gpio_state_t state);
gpio_state_t gpio_read(uint8_t pin);
uint16_t read_sensor(uint8_t sensor_id);
void update_sensors(void);
void display_system_status(void);
void simulate_embedded_operations(void);
uint32_t get_system_uptime(void);
void cleanup_system(void);

// Test functions for CI/CD
int run_unit_tests(void);
int test_gpio_functionality(void);
int test_sensor_operations(void);
int test_memory_management(void);

#endif // MAIN_H