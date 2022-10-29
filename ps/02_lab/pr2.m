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
## @deftypefn {} {@var{retval} =} pr2 (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author:  <andrei@laptop>
## Created: 2022-10-24

function [in_circle, closer_to_center_than_corners] = pr2 (points)
	in_circle = 0;
	closer_to_center_than_corners = 0;
	
	clf; hold on; axis equal; grid on;
	rectangle('Position', [-1 -1 2 2]);
	
	for i=1:points
		point = rand(1, 2) * 2 - 1;
		
		center_dist_sq = sum(point .^ 2);
		current_in_circle = center_dist_sq <= 1^2;
		in_circle += current_in_circle;
		
		corners = [
			-1 -1;
			 1 -1;
			-1  1;
			 1  1;
		];
		
		corner_dists_sq = sum((corners - point) .^ 2, 2);
		corners_closer = corner_dists_sq < center_dist_sq;
		current_closer_to_center_than_corners = not(any(corners_closer));
		closer_to_center_than_corners += current_closer_to_center_than_corners;
		
		corner_dists_sq
		
		if (current_closer_to_center_than_corners)
			plot(point(1), point(2), '*');
		endif
		
	end
endfunction
