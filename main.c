void ejemplo_6_AR(void){

uint8_t led_state = 0, cont_led = 0;
ESTADO_BOTON btn_state = libre; // Iniciamos con botón sin presionar
while(1){
  if (!gpio_get_level(BTN_GPIO)){ // Verificamos si el botón está presionado
  if (btn_state == check_presionado){ // Si estado anterior era check_presinado
    btn_state = presionado; // Cambiar estado a presionado (No fue rebote)
    led_state = ~led_state; // Capturar estado del LED
    gpio_set_level(BLINK_GPIO,led_state); // Actualizar estado del LED
    printf("cambios en el led: %d\n", cont_led++);
      }
    if (btn_state == libre){ // Si estado anterior era libre
      vTaskDelay(10 / portTICK_PERIOD_MS); // Esperamos 10 ms a que pasen los rebotes
      if (!gpio_get_level(BTN_GPIO)){ //Verificamos si el botón sigue presionado
        btn_state = check_presionado; // Actualizamos elestado a check_presionado
        }
      }
    } else { // Verificamos si el botón no está presionado
        if (btn_state == check_liberado){ // Si estado anterior check_liberado
          btn_state = libre; //Cambiar estado a liberado
          }
        if (btn_state == presionado){ // Si estado anterior era presionado
          if (gpio_get_level(BTN_GPIO)){ //Verificamos si botón no está presionado
          vTaskDelay(10 / portTICK_PERIOD_MS);// Esperamos 10ms a que pasen los rebotes
          if (gpio_get_level(BTN_GPIO)){ // Si elbotón sigue sin estar presionado
            btn_state = check_liberado; // Cambiamosestado a check_liberado
            }
          }
        }
      }
    }
  return ;
}



bool debounceButton(int pin, int &lastButtonState, unsigned long &lastDebounceTime, unsigned long debounceDelay = 50) {
  int reading = digitalRead(pin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != lastButtonState) {
      lastButtonState = reading;
      if (lastButtonState == LOW) {
        return true;
      }
    }
  }

  return false;
}
