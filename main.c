#include "main.h"

// Global system state
static system_info_t g_system;
static uint32_t g_system_start_time;

// Initialize the system
error_code_t init_system(void) {
  printf("Initializing embedded system...\n");

  // Initialize system info
  strncpy(g_system.name, PROJECT_NAME, sizeof(g_system.name) - 1);
  strncpy(g_system.version, PROJECT_VERSION, sizeof(g_system.version) - 1);
  strncpy(g_system.author, AUTHOR, sizeof(g_system.author) - 1);
  g_system.uptime = 0;

  // Record start time
  g_system_start_time = (uint32_t)time(NULL);

  // Initialize subsystems
  if (init_gpio() != SUCCESS) {
    printf("ERROR: GPIO initialization failed\n");
    return ERROR_GPIO;
  }

  if (init_sensors() != SUCCESS) {
    printf("ERROR: Sensor initialization failed\n");
    return ERROR_SENSOR;
  }

  printf("System initialization completed successfully!\n");
  return SUCCESS;
}

// Initialize GPIO pins
error_code_t init_gpio(void) {
  printf("Initializing GPIO pins...\n");

  // Initialize all GPIO pins to LOW
  for (int i = 0; i < GPIO_PINS; i++) {
    g_system.gpio_states[i] = GPIO_LOW;
  }

  // Simulate some initial pin states
  g_system.gpio_states[0] = GPIO_HIGH; // Power LED
  g_system.gpio_states[1] = GPIO_HIGH; // Status LED

  printf("GPIO initialization completed\n");
  return SUCCESS;
}

// Initialize sensors
error_code_t init_sensors(void) {
  printf("Initializing sensors...\n");

  for (int i = 0; i < MAX_SENSORS; i++) {
    g_system.sensors[i].id = i;
    g_system.sensors[i].value = 0;
    g_system.sensors[i].timestamp = 0;
    g_system.sensors[i].status = 1; // Active
  }

  printf("Sensor initialization completed\n");
  return SUCCESS;
}

// GPIO write function
void gpio_write(uint8_t pin, gpio_state_t state) {
  if (pin < GPIO_PINS) {
    g_system.gpio_states[pin] = state;
    printf("GPIO Pin %d set to %s\n", pin, state ? "HIGH" : "LOW");
  }
}

// GPIO read function
gpio_state_t gpio_read(uint8_t pin) {
  if (pin < GPIO_PINS) {
    return g_system.gpio_states[pin];
  }
  return GPIO_LOW;
}

// Read sensor value (simulated)
uint16_t read_sensor(uint8_t sensor_id) {
  if (sensor_id >= MAX_SENSORS) {
    return 0;
  }

  // Simulate sensor readings
  uint16_t value = 0;
  switch (sensor_id) {
  case 0:                         // Temperature sensor
    value = 200 + (rand() % 100); // 20.0°C to 30.0°C
    break;
  case 1:                         // Humidity sensor
    value = 400 + (rand() % 300); // 40% to 70%
    break;
  case 2:                          // Pressure sensor
    value = 1000 + (rand() % 100); // 1000-1100 hPa
    break;
  case 3:                  // Light sensor
    value = rand() % 1024; // 0-1023
    break;
  }

  g_system.sensors[sensor_id].value = value;
  g_system.sensors[sensor_id].timestamp = (uint32_t)time(NULL);

  return value;
}

// Update all sensors
void update_sensors(void) {
  for (int i = 0; i < MAX_SENSORS; i++) {
    read_sensor(i);
  }
}

// Get system uptime
uint32_t get_system_uptime(void) {
  return (uint32_t)time(NULL) - g_system_start_time;
}

// Display project information
void display_project_info(void) {
  printf("\n=== %s ===\n", PROJECT_NAME);
  printf("Version: %s\n", PROJECT_VERSION);
  printf("Author: %s\n", AUTHOR);
  printf("Build Date: %s\n", BUILD_DATE);
  printf("Build Time: %s\n", BUILD_TIME);
  printf("======================\n\n");
}

// Display build information
void display_build_info(void) {
  printf("=== Build Information ===\n");
  printf("Compiler: %s\n", __VERSION__);
  printf("Architecture: ");
#ifdef __x86_64__
  printf("x86_64\n");
#elif defined(__arm__)
  printf("ARM\n");
#elif defined(__aarch64__)
  printf("ARM64\n");
#else
  printf("Unknown\n");
#endif
  printf("Standard: C%ld\n", __STDC_VERSION__);
  printf("========================\n\n");
}

// Display system status
void display_system_status(void) {
  printf("=== System Status ===\n");
  printf("System: %s v%s\n", g_system.name, g_system.version);
  printf("Uptime: %u seconds\n", get_system_uptime());

  printf("\nGPIO Status:\n");
  for (int i = 0; i < 4; i++) { // Show first 4 pins
    printf("  Pin %d: %s\n", i, g_system.gpio_states[i] ? "HIGH" : "LOW");
  }

  printf("\nSensor Readings:\n");
  const char *sensor_names[] = {"Temperature", "Humidity", "Pressure", "Light"};
  const char *units[] = {"°C", "%", "hPa", "lux"};
  const float divisors[] = {10.0, 10.0, 1.0, 1.0};

  for (int i = 0; i < MAX_SENSORS; i++) {
    float value = g_system.sensors[i].value / divisors[i];
    printf("  %s: %.1f %s\n", sensor_names[i], value, units[i]);
  }
  printf("====================\n\n");
}

// Simulate embedded operations
void simulate_embedded_operations(void) {
  printf("Starting embedded operations simulation...\n\n");

  // Simulate some GPIO operations
  gpio_write(2, GPIO_HIGH); // Turn on LED
  gpio_write(3, GPIO_LOW);  // Turn off relay

  // Update sensor readings
  update_sensors();

  // Display current status
  display_system_status();

  printf("Embedded operations completed!\n");
}

// Test functions for CI/CD
int test_gpio_functionality(void) {
  printf("Testing GPIO functionality...\n");

  // Test GPIO write/read
  gpio_write(5, GPIO_HIGH);
  if (gpio_read(5) != GPIO_HIGH) {
    printf("GPIO test FAILED\n");
    return -1;
  }

  gpio_write(5, GPIO_LOW);
  if (gpio_read(5) != GPIO_LOW) {
    printf("GPIO test FAILED\n");
    return -1;
  }

  printf("GPIO test PASSED\n");
  return 0;
}

int test_sensor_operations(void) {
  printf("Testing sensor operations...\n");

  // Test sensor readings
  for (int i = 0; i < MAX_SENSORS; i++) {
    uint16_t value = read_sensor(i);
    if (value == 0 && i != 3) { // Light sensor can be 0
      printf("Sensor %d test FAILED\n", i);
      return -1;
    }
  }

  printf("Sensor test PASSED\n");
  return 0;
}

int test_memory_management(void) {
  printf("Testing memory management...\n");

  // Simple memory allocation test
  char *buffer = malloc(BUFFER_SIZE);
  if (buffer == NULL) {
    printf("Memory allocation test FAILED\n");
    return -1;
  }

  // Write and verify data
  memset(buffer, 0xAA, BUFFER_SIZE);
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (buffer[i] != (char)0xAA) {
      printf("Memory test FAILED\n");
      free(buffer);
      return -1;
    }
  }

  free(buffer);
  printf("Memory test PASSED\n");
  return 0;
}

int run_unit_tests(void) {
  printf("\n=== Running Unit Tests ===\n");

  int tests_passed = 0;
  int total_tests = 3;

  if (test_gpio_functionality() == 0)
    tests_passed++;
  if (test_sensor_operations() == 0)
    tests_passed++;
  if (test_memory_management() == 0)
    tests_passed++;

  printf("\nTest Results: %d/%d tests passed\n", tests_passed, total_tests);
  printf("========================\n\n");

  return (tests_passed == total_tests) ? 0 : -1;
}

// Cleanup system resources
void cleanup_system(void) {
  printf("Cleaning up system resources...\n");

  // Turn off all GPIO pins
  for (int i = 0; i < GPIO_PINS; i++) {
    g_system.gpio_states[i] = GPIO_LOW;
  }

  printf("System cleanup completed\n");
}

// Main function
int main(void) {
  printf("========================================\n");
  printf("    CI/CD Embedded Systems Project\n");
  printf("========================================\n");

  // Display project information
  display_project_info();
  display_build_info();

  // Initialize random seed for sensor simulation
  srand((unsigned int)time(NULL));

  // Initialize system
  if (init_system() != SUCCESS) {
    printf("System initialization failed!\n");
    return EXIT_FAILURE;
  }

  // Run unit tests
  if (run_unit_tests() != 0) {
    printf("Unit tests failed!\n");
    cleanup_system();
    return EXIT_FAILURE;
  }

  // Simulate embedded operations
  simulate_embedded_operations();

  // Final status
  printf("=== Final System State ===\n");
  display_system_status();

  // Cleanup
  cleanup_system();

  printf("========================================\n");
  printf("    Project executed successfully!\n");
  printf("========================================\n");

  return EXIT_SUCCESS;
}