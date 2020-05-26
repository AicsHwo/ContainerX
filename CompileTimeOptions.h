#ifndef COMPILE_TIME_OPTIONS
#define COMPILE_TIME_OPTIONS

//#define _DEBUG

#ifdef _DEBUG
	#define DBG(stmt) do{stmt}while(0);
#else
	#define DBG(stmt) ;;
#endif

#ifdef _ENABLE_FUTHUR_DBG_MSG
	#define FURTHUR_DBG_MSG(stmt) do{stmt}while(0)
#else
	#define FURTHUR_DBG_MSG(stmt) ;;
#endif

#endif // COMPILE_TIME_OPTIONS
