fn test() -> i32 { 1 }

fn main() {
	let a = if test() == 1 { "true" } else { "false" };
	println!("{}", a);
}
