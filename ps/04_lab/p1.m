## Copyright (C) 2022
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} p1 (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author:  <andrei@laptop>
## Created: 2022-11-21

function answer = p1 (email_path)
	spam_file = fopen('./files/keywords_spam.txt', 'r');
	spam_vec = textscan(spam_file, '%s'){1};
	fclose(spam_file);
	
	ham_file = fopen('./files/keywords_ham.txt', 'r');
	ham_vec = textscan(ham_file, '%s'){1};
	fclose(ham_file);
	
	email_file = fopen(email_path, 'r');
	email_vec = textscan(email_file, '%s'){1};
	fclose(email_file);
	email_words = unique(email_vec);
	
	words_vec = [spam_vec;ham_vec];
	words = unique([spam_vec;ham_vec])
	
	p_spam = numel(spam_vec) / numel(words_vec);
	p_ham = numel(ham_vec) / numel(words_vec);
	
	for i=1:numel(words)
		p_spam_curr = sum(strcmp(words{i}, spam_vec)) / numel(spam_vec);
		p_ham_curr = sum(strcmp(words{i}, ham_vec)) / numel(ham_vec);
		if ismember(words{i}, email_words)
			p_spam *= p_spam_curr;
			p_ham *= p_ham_curr;
		else
			p_spam *= 1 - p_spam_curr;
			p_ham *= 1 - p_ham_curr;
		end
	end
	
	if p_spam > p_ham
		answer = 'spam';
	else
		answer = 'ham';
	end
endfunction
