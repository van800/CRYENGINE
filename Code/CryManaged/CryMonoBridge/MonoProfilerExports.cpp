#pragma comment(linker, "/export:mono_profiler_set_image_loaded_callback")
#pragma comment(linker, "/export:mono_profiler_set_image_unloaded_callback")
#pragma comment(linker, "/export:mono_profiler_set_assembly_loaded_callback")
#pragma comment(linker, "/export:mono_profiler_set_thread_started_callback")
#pragma comment(linker, "/export:mono_profiler_set_thread_stopped_callback")
#pragma comment(linker, "/export:mono_profiler_set_thread_name_callback")
#pragma comment(linker, "/export:mono_profiler_set_gc_finalizing_callback")
#pragma comment(linker, "/export:mono_profiler_set_exception_throw_callback")
#pragma comment(linker, "/export:mono_profiler_set_gc_event_callback")
#pragma comment(linker, "/export:mono_profiler_enable_allocations")
#pragma comment(linker, "/export:mono_profiler_set_gc_allocation_callback")
#pragma comment(linker, "/export:mono_profiler_set_monitor_contention_callback")
#pragma comment(linker, "/export:mono_profiler_set_monitor_acquired_callback")
#pragma comment(linker, "/export:mono_profiler_set_monitor_failed_callback")
#pragma comment(linker, "/export:mono_profiler_set_jit_begin_callback")
#pragma comment(linker, "/export:mono_profiler_enable_coverage")
#pragma comment(linker, "/export:mono_profiler_set_coverage_filter_callback")
#pragma comment(linker, "/export:mono_profiler_set_sample_hit_callback")
#pragma comment(linker, "/export:mono_profiler_enable_sampling")
#pragma comment(linker, "/export:mono_profiler_set_sample_mode")
#pragma comment(linker, "/export:mono_profiler_set_class_loaded_callback")
#pragma comment(linker, "/export:mono_profiler_set_call_instrumentation_filter_callback")
#pragma comment(linker, "/export:mono_profiler_set_method_enter_callback")
#pragma comment(linker, "/export:mono_profiler_set_method_leave_callback")
#pragma comment(linker, "/export:mono_profiler_set_method_exception_leave_callback")
#pragma comment(linker, "/export:mono_profiler_set_runtime_shutdown_begin_callback")
#pragma comment(linker, "/export:mono_profiler_get_coverage_data")
#pragma comment(linker, "/export:mono_profiler_create")
#pragma comment(linker, "/export:mono_stack_walk_no_il")
#pragma comment(linker, "/export:mono_stack_walk_async_safe")
#pragma comment(linker, "/export:mono_method_full_name")
#pragma comment(linker, "/export:mono_method_signature")
#pragma comment(linker, "/export:mono_signature_get_return_type")
#pragma comment(linker, "/export:mono_type_full_name")
#pragma comment(linker, "/export:mono_signature_get_desc")
#pragma comment(linker, "/export:mono_method_get_class")
#pragma comment(linker, "/export:mono_image_get_filename")
#pragma comment(linker, "/export:mono_object_to_string")
#pragma comment(linker, "/export:mono_string_chars")
#pragma comment(linker, "/export:mono_string_length")
#pragma comment(linker, "/export:mono_object_get_size")
#pragma comment(linker, "/export:mono_class_get_image")
#pragma comment(linker, "/export:mono_method_get_token")
#pragma comment(linker, "/export:mono_image_get_table_rows")
#pragma comment(linker, "/export:mono_assembly_get_name")
#pragma comment(linker, "/export:mono_assembly_name_get_name")
#pragma comment(linker, "/export:mono_assembly_name_get_pubkeytoken")
#pragma comment(linker, "/export:mono_assembly_name_get_version")
#pragma comment(linker, "/export:mono_assembly_get_image")
#pragma comment(linker, "/export:mono_get_method")
#pragma comment(linker, "/export:mono_gc_get_generation")
#pragma comment(linker, "/export:mono_object_get_class")
#pragma comment(linker, "/export:mono_class_get_type")
#pragma comment(linker, "/export:mono_image_get_guid")
#pragma comment(linker, "/export:mono_profiler_set_domain_unloading_callback")
#pragma comment(linker, "/export:mono_domain_get")
#pragma comment(linker, "/export:mono_custom_attrs_from_method")
#pragma comment(linker, "/export:mono_class_get_name")
#pragma comment(linker, "/export:mono_class_get_namespace")
#pragma comment(linker, "/export:mono_image_get_assembly")
#pragma comment(linker, "/export:mono_debug_close_image")
#pragma comment(linker, "/export:mono_image_is_dynamic")
#pragma comment(linker, "/export:mono_method_get_name")
#pragma comment(linker, "/export:mono_profiler_set_assembly_unloading_callback")
#pragma comment(linker, "/export:mono_domain_set_internal")
#pragma comment(linker, "/export:mono_get_root_domain")
#pragma comment(linker, "/export:mono_thread_attach")
#pragma comment(linker, "/export:mono_thread_detach")
#pragma comment(linker, "/export:mono_custom_attrs_from_assembly")
#pragma comment(linker, "/export:mono_signature_get_param_count")
#pragma comment(linker, "/export:mono_signature_get_params")
#pragma comment(linker, "/export:mono_metadata_decode_value")
#pragma comment(linker, "/export:mono_type_get_type")
#pragma comment(linker, "/export:mono_profiler_set_jit_done_callback")
#pragma comment(linker, "/export:mono_jit_info_get_code_start")
#pragma comment(linker, "/export:mono_jit_info_get_code_size")