# https://docs.google.com/document/d/1LV7ONYo23asJI-z-kPyKQO-qrbRjFOr9q2Jz2A7X_7I/edit?usp=sharing

from repo.studentrepo import InMemoryStudentRepo, FileStudentRepo
from repo.disciplinerepo import InMemoryDisciplineRepo, FileDisciplineRepo
from repo.graderepo import InMemoryGradeRepo, FileGradeRepo

from service.studentservice import StudentService
from service.disciplineservice import DisciplineService
from service.gradeservice import GradeService

from domain.validator import \
StudentValidator, DisciplineValidator, GradeValidator

from ui.interactive import UIInteractive

student_validator = StudentValidator()
# student_repo = InMemoryStudentRepo()
student_repo = FileStudentRepo("studentrepo.txt")
student_service = StudentService(student_validator, student_repo)

discipline_validator = DisciplineValidator()
# discipline_repo = InMemoryDisciplineRepo()
discipline_repo = FileDisciplineRepo("disciplinerepo.txt")
discipline_service = DisciplineService(discipline_validator, discipline_repo)

grade_validator = GradeValidator()
# grade_repo = InMemoryGradeRepo()
grade_repo = FileGradeRepo("graderepo.txt")
grade_service = GradeService(grade_validator, grade_repo, student_repo, discipline_repo)

ui_interactive = UIInteractive(student_service, discipline_service, grade_service)
ui_interactive.run()