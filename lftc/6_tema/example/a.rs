fn main() {
  let mut a = 0;
  write!("a = ");
  read!("%d", &mut a);

  let mut b = 0;
  write!("b = ");
  read!("%d", &mut b);

  let mut c = a*a + b - a;
  c = c + 1;
  write!("%d %d\n", a, c);
}
