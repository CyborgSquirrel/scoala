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
## @deftypefn {} {@var{retval} =} aranj2 (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author:  <andrei@laptop>
## Created: 2022-10-10

function retval = aranj2 (v, k)
	retval = [];
	p = perms(1:k);
	c = nchoosek(v, k);
	for i=1:length(c)
		## for j=1:length(p)
		## 	retval = [retval; c(i,p(j,:))];
		## end
		retval = [retval; c()]
	end
endfunction
