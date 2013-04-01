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
void menuPC(void);

void menu_deinitAll(void);
void menuPC_DeInit(void);
void menuSetupRamp_DeInit(void);
void menuSetup_DeInit(void);
void menuRamp_DeInit(void);
void menuDigital_DeInit(void);
void menuAnalog_DeInit(void);
void mainMenu_DeInit(void);
void menuTest_DeInit(void);
void controlS2(void);