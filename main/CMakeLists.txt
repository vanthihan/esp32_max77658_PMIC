# Edit following two lines to set component requirements (see docs)
#set(COMPONENT_REQUIRES )
#set(COMPONENT_PRIV_REQUIRES )
#
#set(COMPONENT_SRCS "main.c")
#set(COMPONENT_ADD_INCLUDEDIRS "")

idf_component_register(SRCS "main.c"
							"bsp/bsp_mem.c"
							"bsp/bsp_mutex.c"
							"bsp/i2c_bus.c"
							"bsp/bsp.c"
							"component/pmic/max77658_reg.c"
							"task/pmic_task.c"

						INCLUDE_DIRS "." 
							"./bsp" 
							"./component" 
							"./component/pmic"
							"./task"
							)
