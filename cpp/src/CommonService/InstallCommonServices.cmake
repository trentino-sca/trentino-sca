### get the installation path from env variable 
#set(trentino_home $ENV{TRENTINO_HOME})

#####################################Install Preference Service
set(project_name PreferenceService)

#install conrtibution dir
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${common_service_dir}/${project_name}/" ${trentino_home}/CommonService/PreferenceService)

#install header files related to contrbution
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${common_service_dir}/PreferenceService/services/TrentinoSystem.h ${trentino_home}/include/PreferenceService/TrentinoSystem.h)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${common_service_dir}/PreferenceService/services/TrentinoSystemPreference.h ${trentino_home}/include/PreferenceService/TrentinoSystemPreference.h)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${common_service_dir}/PreferenceService/services/TrentinoSystemPreferenceService.h ${trentino_home}/include/PreferenceService/TrentinoSystemPreferenceService.h)

#####################################Install Preference Service end 
