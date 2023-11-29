fn main() {
  let mut input = String::new();
  let stdin = std::io::stdin();

  stdin.read_line(&mut input).unwrap();
	let mut n: u32 = input.trim().parse().unwrap();
	input.clear();

	let mut sum = 0;

	while n > 0 {
		n = n - 1;

	  stdin.read_line(&mut input).unwrap();
		let a: u32 = input.trim().parse().unwrap();
		input.clear();

		sum = sum + a;
	}

	println!("suma = {}", sum);
}
