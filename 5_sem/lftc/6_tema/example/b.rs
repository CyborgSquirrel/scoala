fn main() {
  write!("Introduceti factorii unei ecuatii de gradul 2\n");

	let a = 0;
  write!("a = ");
  read!("%d", &mut a);

	let b = 0;
  write!("b = ");
  read!("%d", &mut b);

	let c = 0;
  write!("c = ");
  read!("%d", &mut c);

	let delta = b*b - 4*a*c;
	write!("delta = %d\n", delta);
}
