/* Minimal Linux-like double-linked list helper functions test
 *
 * Copyright (c) 2012-2014, Sven Eckelmann <sven@narfation.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "../list.h"
#include <assert.h>
#include <stdlib.h>

struct listitem {
	int i;
	struct list_head list;
};

int main(void)
{
	struct list_head testlist, testlist2;
	struct listitem *item, *is;
	int i;

	INIT_LIST_HEAD(&testlist);
	INIT_LIST_HEAD(&testlist2);

	assert(list_empty(&testlist));
	assert(list_empty(&testlist2));

	for (i = -5; i < 0; i++) {
		item = (struct listitem *)malloc(sizeof(*item));
		assert(item);
		item->i = i;
		list_add_tail(&item->list, &testlist);
	}

	assert(!list_empty(&testlist));

	for (i = 0; i < 5; i++) {
		item = (struct listitem *)malloc(sizeof(*item));
		assert(item);
		item->i = i;
		list_add_tail(&item->list, &testlist2);
	}

	assert(!list_empty(&testlist2));

	list_for_each_entry_safe_t(item, is, &testlist2, struct listitem, list)
		list_move_tail(&item->list, &testlist);

	assert(list_empty(&testlist2));

	i = -5;
	list_for_each_entry_safe_t(item, is, &testlist, struct listitem, list) {
		assert(item->i == i);
		list_del(&item->list);
		free(item);
		i++;
	}

	assert(i == 5);
	assert(list_empty(&testlist));

	return 0;
}
