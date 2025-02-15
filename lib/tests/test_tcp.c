/*****************************************************************************
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *****************************************************************************/

#include "common.h"
#include "utils_tcp.h"
#include "tap.h"

int main(void) {
	char **server_expect;
	int server_expect_count = 3;

	plan_tests(9);

	server_expect = malloc(sizeof(char *) * server_expect_count);

	server_expect[0] = strdup("AA");
	server_expect[1] = strdup("bb");
	server_expect[2] = strdup("CC");

	ok(np_expect_match("AA bb CC XX", server_expect, server_expect_count, NP_MATCH_EXACT) == NP_MATCH_SUCCESS,
	   "Test matching any string at the beginning (first expect string)");
	ok(np_expect_match("bb AA CC XX", server_expect, server_expect_count, NP_MATCH_EXACT) == NP_MATCH_SUCCESS,
	   "Test matching any string at the beginning (second expect string)");
	ok(np_expect_match("b", server_expect, server_expect_count, NP_MATCH_EXACT) == NP_MATCH_RETRY,
	   "Test matching any string at the beginning (substring match)");
	ok(np_expect_match("XX bb AA CC XX", server_expect, server_expect_count, NP_MATCH_EXACT) == NP_MATCH_FAILURE,
	   "Test with strings not matching at the beginning");
	ok(np_expect_match("XX CC XX", server_expect, server_expect_count, NP_MATCH_EXACT) == NP_MATCH_FAILURE, "Test matching any string");
	ok(np_expect_match("XX", server_expect, server_expect_count, 0) == NP_MATCH_RETRY, "Test not matching any string");
	ok(np_expect_match("XX AA bb CC XX", server_expect, server_expect_count, NP_MATCH_ALL) == NP_MATCH_SUCCESS,
	   "Test matching all strings");
	ok(np_expect_match("XX bb CC XX", server_expect, server_expect_count, NP_MATCH_ALL) == NP_MATCH_RETRY, "Test not matching all strings");
	ok(np_expect_match("XX XX", server_expect, server_expect_count, NP_MATCH_ALL) == NP_MATCH_RETRY,
	   "Test not matching any string (testing all)");

	return exit_status();
}
