/*
 * Minimal compile-time stub of the sentry-native public API.
 *
 * Included by the kDrive sources instead of the real <sentry.h>.  Every
 * function is a no-op and the library never opens a network connection.
 * This is used to build kDrive without the proprietary telemetry service
 * configured by upstream and without pulling sentry-native (and its
 * bundled crashpad) into Fedora.
 *
 * The symbol set mirrors what kDrive 3.8.7 actually uses:
 *   $ grep -rhoE '\bsentry_[a-z_0-9]+\b' src test --include=*.cpp --include=*.h | sort -u
 *
 * License: MIT (this file contains no code from sentry-native)
 */
#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque handles. */
typedef struct sentry_options_s sentry_options_t;
typedef struct sentry_transaction_s sentry_transaction_t;
typedef struct sentry_span_s sentry_span_t;
typedef struct sentry_transaction_context_s sentry_transaction_context_t;

/* kDrive uses value._bits to detect tagged values when reading events. */
typedef struct sentry_value_s {
    uint64_t _bits;
} sentry_value_t;

typedef struct sentry_ucontext_s {
    void *signum;
} sentry_ucontext_t;

typedef enum {
    SENTRY_LEVEL_DEBUG = -1,
    SENTRY_LEVEL_INFO = 0,
    SENTRY_LEVEL_WARNING = 1,
    SENTRY_LEVEL_ERROR = 2,
    SENTRY_LEVEL_FATAL = 3
} sentry_level_t;

typedef enum {
    SENTRY_SPAN_STATUS_OK = 0,
    SENTRY_SPAN_STATUS_CANCELLED = 1,
    SENTRY_SPAN_STATUS_ABORTED = 2
} sentry_span_status_t;

typedef enum {
    SENTRY_VALUE_TYPE_NULL = 0,
    SENTRY_VALUE_TYPE_BOOL,
    SENTRY_VALUE_TYPE_INT32,
    SENTRY_VALUE_TYPE_DOUBLE,
    SENTRY_VALUE_TYPE_STRING,
    SENTRY_VALUE_TYPE_LIST,
    SENTRY_VALUE_TYPE_OBJECT
} sentry_value_type_t;

typedef sentry_value_t (*sentry_before_send_t)(sentry_value_t event, void *hint, void *closure);
typedef sentry_value_t (*sentry_on_crash_t)(const sentry_ucontext_t *uctx, sentry_value_t event, void *closure);

/* Options. */
sentry_options_t *sentry_options_new(void);
void sentry_options_set_dsn(sentry_options_t *opts, const char *dsn);
void sentry_options_set_release(sentry_options_t *opts, const char *release);
void sentry_options_set_environment(sentry_options_t *opts, const char *environment);
void sentry_options_set_debug(sentry_options_t *opts, int debug);
void sentry_options_set_max_breadcrumbs(sentry_options_t *opts, size_t max_breadcrumbs);
void sentry_options_set_max_spans(sentry_options_t *opts, size_t max_spans);
void sentry_options_set_traces_sample_rate(sentry_options_t *opts, double traces_sample_rate);
void sentry_options_set_before_send(sentry_options_t *opts, sentry_before_send_t func, void *closure);
void sentry_options_set_on_crash(sentry_options_t *opts, sentry_on_crash_t func, void *closure);
void sentry_options_set_handler_path(sentry_options_t *opts, const char *path);
void sentry_options_set_handler_pathw(sentry_options_t *opts, const wchar_t *path);
void sentry_options_set_database_path(sentry_options_t *opts, const char *path);
void sentry_options_set_database_pathw(sentry_options_t *opts, const wchar_t *path);

/* Lifecycle. */
int sentry_init(sentry_options_t *options);
void sentry_close(void);

/* Values. */
sentry_value_t sentry_value_new_null(void);
sentry_value_t sentry_value_new_object(void);
sentry_value_t sentry_value_new_string(const char *value);
sentry_value_t sentry_value_new_breadcrumb(const char *type, const char *message);
sentry_value_t sentry_value_new_message_event(sentry_level_t level, const char *logger, const char *text);
int sentry_value_set_by_key(sentry_value_t value, const char *k, sentry_value_t v);
sentry_value_type_t sentry_value_get_type(sentry_value_t value);
int sentry_value_is_true(sentry_value_t value);
int32_t sentry_value_as_int32(sentry_value_t value);
double sentry_value_as_double(sentry_value_t value);
const char *sentry_value_as_string(sentry_value_t value);

/* Events, users, tags. */
void sentry_capture_event(sentry_value_t event);
void sentry_add_breadcrumb(sentry_value_t breadcrumb);
void sentry_set_user(sentry_value_t user);
void sentry_remove_user(void);
void sentry_set_tag(const char *key, const char *value);
void sentry_remove_tag(const char *key);

/* Performance traces. */
sentry_transaction_context_t *sentry_transaction_context_new(const char *name, const char *op);
sentry_transaction_t *sentry_transaction_start(sentry_transaction_context_t *context, sentry_value_t sampling_ctx);
void sentry_transaction_finish(sentry_transaction_t *txn);
void sentry_transaction_set_status(sentry_transaction_t *txn, sentry_span_status_t status);
sentry_span_t *sentry_transaction_start_child(sentry_transaction_t *parent, const char *op, const char *description);
sentry_span_t *sentry_span_start_child(sentry_span_t *parent, const char *op, const char *description);
void sentry_span_set_status(sentry_span_t *span, sentry_span_status_t status);
void sentry_span_finish(sentry_span_t *span);

#ifdef __cplusplus
}
#endif
