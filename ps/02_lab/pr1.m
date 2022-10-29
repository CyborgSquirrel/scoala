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
## @deftypefn {} {@var{retval} =} pr1 (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author:  <andrei@laptop>
## Created: 2022-10-24

function retval = pr1 (simulations, students)
	retval = 0;
	for i=1:simulations
		len = length(unique(randi(365,1,students)));
		if (len < students)
			retval += 1;
		endif
	end
	retval /= simulations;
endfunction
