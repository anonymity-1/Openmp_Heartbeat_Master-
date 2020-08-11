/* 
 * File:   Heartbeat_Support_OpenMP.h
 * Author: weidong
 *
 * Created on November 29, 2014, 1:19 PM
 */

#ifndef HEARTBEAT_SUPPORT_OPENMP_H
#define	HEARTBEAT_SUPPORT_OPENMP_H
#define NUM_THREADS 8
#define HEART_FREQUENCY 10

typedef struct {
  long beat;                 // Heartbeat 
  int  threadnum;                   // used for recongnizing each beat
  int  loopnum;
  long timestamp;            // used for record each beat time
  double heartbeat_rate;     // refeclt the beat frequency
} heartbeat_log_t;           // struct used for record each beat data

typedef struct {
  long index;
  pthread_t tid; 
  double heartbeat_real_value;
  double heartbeat_rate;
  long timestamp;
} heartbeat_memory_t;

typedef struct{
    int type;
    pthread_t tid_rpt;
    int index_rpt;
    pthread_t tid_rptd;
    int index_rptd;
} heartbeat_failed_log_t;

typedef struct{
   pthread_t tid;             // used for multi-threads as saving a thread number
   long counter;               // beat counter
   long buffer_index;
   long buffer_to_file;       // at one time write how many buffer size to file
   FILE* _file; 
   heartbeat_failed_log_t* _log_f;
   pthread_mutex_t _mutex;
} heartbeat_failedinfo_profile_t;

typedef struct {
    long amount;
    int index;
    pthread_t tid;
    heartbeat_memory_t* p;     // Pointer to the unit of memory. 
    pthread_t *pt;
    heartbeat_memory_t* last;     // Pointer to the unit of memory.
    int64_t mean_freq;
    pthread_mutex_t mutex;     // Mutex for some memory operations. 
    int buzy_wait_flag;
    int normal_exit_flag;
} heartbeat_sequence;


typedef struct {
  pthread_t tid;             // used for multi-threads as saving a thread number
  long counter;               // beat counter
  long buffer_to_file;       // at one time write how many buffer size to file
  long buffer_index;         // buffer index
  long fcounter;
  long fbuffer_to_file;
  long fbuffer_index;
  int64_t first_timestamp;   // timestamp for last time
  int64_t last_timestamp;    // timestamp for current time
  int64_t acc_timestamp_first;
  int64_t acc_timestamp_last;
  int64_t time_temp;
  int acc_index;
  long current_index;        // current index
  int64_t max;                  // max number of heartbeats in a group
  long interval;             // interval between two beats (nanosecond)
  int frequency;             // input 2, 4, 5, or ... n denotes total number/n times
  int64_t mean_freq;
  int cycle;                 // used for total number of loop times
  heartbeat_log_t* log;      // pointer for log
  heartbeat_memory_t* memory; //pointer for memory
  heartbeat_failed_log_t* flog;
  FILE*  text_file;           // pointer to file saving heartbeat record.
  FILE*  fault_file;
  pthread_mutex_t mutex;     // mutex for some memory operations. 
} heartbeat_profile_t;       // heartbeat profile.

typedef struct {
  int  index;
  long num_l;              //  
  double num_d;            // 
  double mean;             //
  double variance;         //
} heartbeat_faultinjection_num_t;                   // 

enum pthread_status_t
{
  normal_exit=-1,
  abnormal_exit=0,
  alive_running=1,
  alive_busywait=2,
  NoStatus=3
};

typedef struct {
  int index;
  int start_flag;
  int loopnum;
  pthread_t tid;
  enum pthread_status_t st;
  enum pthread_status_t last_st;
  int is_rept; //==2 report 
} heartbeat_ring_queue;                   // 


#ifdef	__cplusplus
extern "C" {
#endif

int L_Heartbeat_OpenMP_Init();

int L_Heartbeat_OpenMP_Generate(int threadnum,int loopnum, int iter);

int L_Heartbeat_OpenMP_Monitor(int iter,int loopnum);                        

void L_Heartbeat_OpenMP_Finished();

#ifdef	__cplusplus
}
#endif

#endif	/* HEARTBEAT_SUPPORT_OPENMP_H */

