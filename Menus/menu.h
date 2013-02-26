#define MENU_MAIN			0
#define MENU_ANALOG		1
#define MENU_DIGITAL	2
#define MENU_RAMP			3
#define MENU_SETUP		4
#define MENU_SETUPRAMP	5
#define MENU_TEST	6


#define BTN_UP	1
#define BTN_DOWN	0
	
void menu_displayRPM(uint8_t x, uint8_t y);

void menuSetupRamp(void);
void menuSetup(void);
void menuRamp(void);
void menuDigital(void);
void menuAnalog(void);
void mainMenu(void);
void menuTest(void);