/*Symbols defined in the linker script */
extern uint32_t _endstack;
extern uint32_t _endtext;
extern uint32_t _startdata;
extern uint32_t _enddata;
extern uint32_t _startbss;
extern uint32_t _endbss;

/* Function prototypes */
void Reset_Handler(void);
int main(void);

/* Exception and Interrupt Handlers */
void NMI_Handler(void)__attribute__((weak,alias("Default_Handler")));
void HardFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__ ((weak, alias("Default_Handler")));

/* Vector Table */
uint32_t vector_tbl[] __attribute__((section(".isr_vector_tbl")))={
	(uint32_t)&_endstack,
	(uint32_t)&Reset_Handler,
	(uint32_t)&NMI_Handler,
	(uint32_t)&HardFault_Handler,
	(uint32_t)&MemManage_Handler,
}

/* Default handler that enters an infinite loop */
void Default_Handler(void)
{
	while(1){}
}

/* Reset Handler */
void Reset_Handler(void)
{
	// Calculate the sizes of the .data and .bss sections
	uint32_t data_mem_size =  (uint32_t)&_enddata - (uint32_t)&_startdata;
	uint32_t bss_mem_size  =   (uint32_t)&_endbss - (uint32_t)&_startbss;

	/* Convert byte sizes to 32-bit word counts to match uint32_t* copies (4 == sizeof(uint32_t)) */
    data_mem_size /= 4;
    bss_mem_size  /= 4;
	
	// Initialize pointers to the source and destination of the .data section
	uint32_t *p_src_mem =  (uint32_t *)&_endtext;
	uint32_t *p_dest_mem = (uint32_t *)&_startdata;
	
	/*Copy .data section from FLASH to SRAM*/
	for(uint32_t i = 0; i < data_mem_size; i++  )
	{
		*p_dest_mem++ = *p_src_mem++;
	}
	
	// Initialize the .bss section to zero in SRAM
	p_dest_mem =  (uint32_t *)&_startbss;
	
	for(uint32_t i = 0; i < bss_mem_size; i++)
	{
		/*Set bss section to zero*/  
		*p_dest_mem++ = 0;
	}
	
	// Call the application's main function.
	main();
}