from ui import UiConsole

from repo import RepoEvent
from srv import SrvEvent

repo_event = RepoEvent("repo_event.txt")
srv_event = SrvEvent(repo_event)

ui = UiConsole(srv_event)
ui.run()