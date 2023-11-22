fn main() {
  let mut input = String::new();
  let stdin = std::io::stdin();

  stdin.read_line(&mut input).unwrap();
	let mut a: u32 = input.trim().parse().unwrap();
	input.clear();

  stdin.read_line(&mut input).unwrap();
	let mut b: u32 = input.trim().parse().unwrap();
	input.clear();

	while b > 0 {
		let at = b;
		let bt = a % b;

		a = at;
		b = bt;
	}

	println!("CMMDC este {}", a);
}
