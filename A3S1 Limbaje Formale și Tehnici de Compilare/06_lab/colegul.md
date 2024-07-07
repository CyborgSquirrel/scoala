Automate:
  states: Map<string, State>
  startState: string

State:
  name: string
  transitions: Map<string, List<State>>
  final: bool
