struct A {
  b: i32,
}

fn main() {
  let mut input = String::new();
  let stdin = std::io::stdin();

  stdin.read_line(&mut input).unwrap();
	let radius: f32 = input.trim().parse().unwrap();
	input.clear();

	let perimeter = std::f32::consts::PI * 2. * radius;
	let area = std::f32::consts::PI * radius * radius;

	println!("perimeter = {}", perimeter);
	println!("area = {}", area);
}
