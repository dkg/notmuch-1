/* indexopts.c - options for indexing messages (currently a stub)
 *
 * Copyright © 2017 Daniel Kahn Gillmor
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see https://www.gnu.org/licenses/ .
 *
 * Author: Daniel Kahn Gillmor <dkg@fifthhorseman.net>
 */

#include "notmuch-private.h"

notmuch_indexopts_t *
notmuch_database_get_default_indexopts (notmuch_database_t *db)
{
    notmuch_indexopts_t *ret = talloc_zero (db, notmuch_indexopts_t);
    if (!ret)
	return ret;

    char * try_decrypt;
    notmuch_status_t err = notmuch_database_get_config (db, "index.try_decrypt", &try_decrypt);
    if (err)
	return ret;

    if (try_decrypt &&
	((!(strcasecmp(try_decrypt, "true"))) ||
	 (!(strcasecmp(try_decrypt, "yes"))) ||
	 (!(strcasecmp(try_decrypt, "1")))))
	notmuch_indexopts_set_try_decrypt (ret, true);

    free (try_decrypt);
    return ret;
}

notmuch_status_t
notmuch_indexopts_set_try_decrypt (notmuch_indexopts_t *indexopts,
				   notmuch_bool_t try_decrypt)
{
    if (!indexopts)
	return NOTMUCH_STATUS_NULL_POINTER;
    indexopts->crypto.decrypt = try_decrypt;
    return NOTMUCH_STATUS_SUCCESS;
}

notmuch_bool_t
notmuch_indexopts_get_try_decrypt (const notmuch_indexopts_t *indexopts)
{
    if (!indexopts)
	return false;
    return indexopts->crypto.decrypt;
}

void
notmuch_indexopts_destroy (notmuch_indexopts_t *indexopts)
{
    talloc_free (indexopts);
}
