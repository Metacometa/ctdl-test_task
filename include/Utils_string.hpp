#include <string>

const std::string settings_str = "settings";
const std::string period_str = "period";


const std::string metrics_str = "metrics";
const std::string type_str = "type";

const std::string cpu_str = "cpu";
const std::string cpu_ids_str = "ids";


const std::string memory_str = "memory";
const std::string spec_str = "spec";

const std::string used_str = "used";
const std::string free_str = "free";


const std::string outputs_str = "outputs";

const std::string console_str = "console";
const std::string log_str = "log";
const std::string path_str = "path";

//errors
const std::string settings_error_msg = "No 'settings' value";
const std::string period_error_msg = "No 'settings[period]' value";


const std::string metrics_init_error_msg = "No 'metrics' value";
const std::string type_error_msg = "One of objects does not have 'type' value";
const std::string metrics_uknown_type_error_msg = "Unknown 'type' value: "; 

const std::string cpu_ids_error_msg = "No 'ids' value in type 'cpu'"; 
const std::string cpu_ids_array_error_msg = "'ids' values are not array"; 
const std::string cpu_ids_number_error_msg = "One of 'ids' values are not number";

const std::string spec_error_msg = "No 'spec' value in type 'memory'";
const std::string spec_array_error_msg = "'spec' values are not array"; 
const std::string spec_string_error_msg = "One of 'spec' values are not string";
const std::string unknown_spec_error_msg = "Unknown 'spec' value: ";

const std::string outputs_error_msg =  "No 'outputs' value"; 
const std::string path_error_msg =  "No 'path' value in type 'log'"; 
const std::string path_string_error_msg = "Path value are not string";

const std::string proc_stat_error_msg = "Cant't open: ";

//utils
const std::string filestat_str = "/proc/stat";