fn test() -> i32 { 0x1 }

fn main() {
	let a = if test() == 1 { "true" } else { "false" };
	let b = 1.23 + 1.;
	println!("{}", a);
}
