/*
 * No-op implementation of the sentry-native API used by kDrive.
 * See sentry.h in this directory.  License: MIT.
 */
#include "sentry.h"

#include <stdlib.h>
#include <string.h>

/* The structs are opaque to callers; the definitions only exist so the
 * library has something to hand out. */
struct sentry_options_s {
    char *dsn;
};
struct sentry_transaction_s {
    int dummy;
};
struct sentry_span_s {
    int dummy;
};
struct sentry_transaction_context_s {
    int dummy;
};

static const sentry_value_t sentry_value_null_value = {0};

sentry_options_t *sentry_options_new(void) {
    return calloc(1, sizeof(sentry_options_t));
}

void sentry_options_set_dsn(sentry_options_t *opts, const char *dsn) {
    (void) opts;
    (void) dsn;
}
void sentry_options_set_release(sentry_options_t *opts, const char *release) {
    (void) opts;
    (void) release;
}
void sentry_options_set_environment(sentry_options_t *opts, const char *environment) {
    (void) opts;
    (void) environment;
}
void sentry_options_set_debug(sentry_options_t *opts, int debug) {
    (void) opts;
    (void) debug;
}
void sentry_options_set_max_breadcrumbs(sentry_options_t *opts, size_t max_breadcrumbs) {
    (void) opts;
    (void) max_breadcrumbs;
}
void sentry_options_set_max_spans(sentry_options_t *opts, size_t max_spans) {
    (void) opts;
    (void) max_spans;
}
void sentry_options_set_traces_sample_rate(sentry_options_t *opts, double traces_sample_rate) {
    (void) opts;
    (void) traces_sample_rate;
}
void sentry_options_set_before_send(sentry_options_t *opts, sentry_before_send_t func, void *closure) {
    (void) opts;
    (void) func;
    (void) closure;
}
void sentry_options_set_on_crash(sentry_options_t *opts, sentry_on_crash_t func, void *closure) {
    (void) opts;
    (void) func;
    (void) closure;
}
void sentry_options_set_handler_path(sentry_options_t *opts, const char *path) {
    (void) opts;
    (void) path;
}
void sentry_options_set_handler_pathw(sentry_options_t *opts, const wchar_t *path) {
    (void) opts;
    (void) path;
}
void sentry_options_set_database_path(sentry_options_t *opts, const char *path) {
    (void) opts;
    (void) path;
}
void sentry_options_set_database_pathw(sentry_options_t *opts, const wchar_t *path) {
    (void) opts;
    (void) path;
}

int sentry_init(sentry_options_t *options) {
    free(options);
    return 0;
}

void sentry_close(void) {}

sentry_value_t sentry_value_new_null(void) {
    return sentry_value_null_value;
}
sentry_value_t sentry_value_new_object(void) {
    return sentry_value_null_value;
}
sentry_value_t sentry_value_new_string(const char *value) {
    (void) value;
    return sentry_value_null_value;
}
sentry_value_t sentry_value_new_breadcrumb(const char *type, const char *message) {
    (void) type;
    (void) message;
    return sentry_value_null_value;
}
sentry_value_t sentry_value_new_message_event(sentry_level_t level, const char *logger, const char *text) {
    (void) level;
    (void) logger;
    (void) text;
    return sentry_value_null_value;
}
int sentry_value_set_by_key(sentry_value_t value, const char *k, sentry_value_t v) {
    (void) value;
    (void) k;
    (void) v;
    return 0;
}
sentry_value_type_t sentry_value_get_type(sentry_value_t value) {
    (void) value;
    return SENTRY_VALUE_TYPE_NULL;
}
int sentry_value_is_true(sentry_value_t value) {
    (void) value;
    return 0;
}
int32_t sentry_value_as_int32(sentry_value_t value) {
    (void) value;
    return 0;
}
double sentry_value_as_double(sentry_value_t value) {
    (void) value;
    return 0.0;
}
const char *sentry_value_as_string(sentry_value_t value) {
    (void) value;
    return "";
}

void sentry_capture_event(sentry_value_t event) {
    (void) event;
}
void sentry_add_breadcrumb(sentry_value_t breadcrumb) {
    (void) breadcrumb;
}
void sentry_set_user(sentry_value_t user) {
    (void) user;
}
void sentry_remove_user(void) {}
void sentry_set_tag(const char *key, const char *value) {
    (void) key;
    (void) value;
}
void sentry_remove_tag(const char *key) {
    (void) key;
}

sentry_transaction_context_t *sentry_transaction_context_new(const char *name, const char *op) {
    (void) name;
    (void) op;
    return calloc(1, sizeof(sentry_transaction_context_t));
}
sentry_transaction_t *sentry_transaction_start(sentry_transaction_context_t *context, sentry_value_t sampling_ctx) {
    (void) context;
    (void) sampling_ctx;
    return calloc(1, sizeof(sentry_transaction_t));
}
void sentry_transaction_finish(sentry_transaction_t *txn) {
    free(txn);
}
void sentry_transaction_set_status(sentry_transaction_t *txn, sentry_span_status_t status) {
    (void) txn;
    (void) status;
}
sentry_span_t *sentry_transaction_start_child(sentry_transaction_t *parent, const char *op, const char *description) {
    (void) parent;
    (void) op;
    (void) description;
    return calloc(1, sizeof(sentry_span_t));
}
sentry_span_t *sentry_span_start_child(sentry_span_t *parent, const char *op, const char *description) {
    (void) parent;
    (void) op;
    (void) description;
    return calloc(1, sizeof(sentry_span_t));
}
void sentry_span_set_status(sentry_span_t *span, sentry_span_status_t status) {
    (void) span;
    (void) status;
}
void sentry_span_finish(sentry_span_t *span) {
    free(span);
}
