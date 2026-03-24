#ifndef PP_FLEXNET_LC_H_API
#define PP_FLEXNET_LC_H_API



bool pp_lc_init();
void pp_lc_set_licensedir(const char* licensedir);
bool pp_lc_checkout(const char* feature,const char* ver);
bool pp_lc_checkin(const char*feature);
bool pp_lc_reject();
int pp_lc_exit();


#endif