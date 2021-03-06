#include <stdio.h>
#include <stdlib.h>

#include "shared.h"
#include "database.h"
#include "master_modules.h"

void *get_module(void *e, int i) {
    return &((module*)e)[i];
}

int get_module_id(void *e) {
    return ((module*)e)->id;
}

int set_module_id(void *e, int id) {
    ((module*)e)->id = id;
    return id;
}

module *select_module(FILE *db, module *m, int id) {
    if (id != -1) {
        createidx(db, module_entity, sizeof(module), m, get_module_id);
    }
    return select(db, module_entity, sizeof(module), m, id, get_module, get_module_id, set_module_id);
}

int insert_module(FILE *db, module *m, module *data) {
    return insert(db, sizeof(module), m, data, get_module_id, set_module_id);
}

int update_module(FILE *db, module *m, module *data, int id) {
    createidx(db, module_entity, sizeof(module), m, get_module_id);
    return update(db, module_entity, sizeof(module), m, data, id, get_module_id, set_module_id);
}

int delete_module(FILE *db, module *m, int id) {
    int status = 0;
    module *data = malloc(sizeof(module));
    data = select_module(db, data, id);
    if (data != NULL) {
        data->deletion_flag = 1;
        status = update_module(db, m, data, id);
    }
    free(data);
    return status;
}
