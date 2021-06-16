#include "M5Atom.h"
#include <chrono>
#include <thread>

class MyTask: public Task
{
  public:
    explicit MyTask(uint16_t taskSize = 10240, uint8_t priority = 5)
      : Task("say-hello")
    {}

    void run(void* /*data*/) override
    {
      while (true) {
        Serial.println("Sub task");

        // Sleep won't work!
        std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 });
      }
  }
};

auto t = MyTask();

void setup()
{
  M5.begin(true, false, true);
  delay(50);

  // Start sub-task
  t.start();
}

void loop()
{
  M5.update();

  // Do something in the main thread
  Serial.println("Main task");
  delay(4000);
}
