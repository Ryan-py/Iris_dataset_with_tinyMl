#include "EloquentTinyML.h"
#include "eloquent_tinyml/tensorflow.h"

#include "iris_model.h"

#define IN 4
#define OUT 3
#define ARENA 7*1024

Eloquent::TinyML::TensorFlow::TensorFlow<IN, OUT, ARENA> tf;

void setup() {
    Serial.begin(115200);
    tf.begin(model);
}

void loop() {
 float input[4] ;
 readSerialInput(input);


    tf.predictClass(input);

    Serial.print("Setosa score: ");
    Serial.println(tf.getScoreAt(0));
    Serial.print("Versicolor score: ");
    Serial.println(tf.getScoreAt(1));
    Serial.print("Virginica score: ");
    Serial.println(tf.getScoreAt(2));
    delay(1000);
}

void readSerialInput(float inputArray[]) {
  // Wait for input from the serial monitor
  while (!Serial.available()) {
    // Wait until data is available
  }

  // Read input values from the serial monitor
  String inputString = Serial.readStringUntil('\n');  // Read the input string
  inputString.trim();  // Remove leading/trailing whitespaces
  String inputValues[4];  // Array to store input values as strings
  int index = 0;  // Index for input values array

  // Extract individual values from the input string
  int startIndex = 0;
  int endIndex = inputString.indexOf(',');
  while (endIndex >= 0 && index < 4) {
    inputValues[index] = inputString.substring(startIndex, endIndex);
    startIndex = endIndex + 1;
    endIndex = inputString.indexOf(',', startIndex);
    index++;
  }
  // Extract the last value from the input string
  if (index < 4) {
    inputValues[index] = inputString.substring(startIndex);
    index++;
  }

  // Check if the input values are valid
  if (index == 4) {
    // Convert input values to floats and store them in the input array
    for (int i = 0; i < 4; ++i) {
      inputArray[i] = inputValues[i].toFloat();
    }
  } else {
    Serial.println("Invalid input format!");
  }

  // Clear the serial monitor
  while (Serial.available()) {
    Serial.read();
  }
}
