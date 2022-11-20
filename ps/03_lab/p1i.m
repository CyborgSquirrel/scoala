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
## @deftypefn {} {@var{retval} =} p1i (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author:  <andrei@laptop>
## Created: 2022-11-07

function retval = p1i (simulations)
	retval = 0;
	for i=1:simulations
		population = [1, 1, 1, 1, 1, 2, 2, 2, 3, 3];
		sample = randsample(population, 3);
		event_A = 0;
		for j=1:length(sample)
			if sample(j) == 1
				event_A = 1;
			end
		end
		retval += event_A;
	end
	retval /= simulations;
endfunction
