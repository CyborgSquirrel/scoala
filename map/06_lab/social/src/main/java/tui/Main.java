package tui;

import domain.Friendship;
import domain.User;
import repo.exception.ItemDoesntExistException;
import repo.friendship.RepoFriendship;
import repo.friendship.RepoFriendshipDB;
import repo.user.RepoUser;
import repo.user.RepoUserDB;
import service.exception.DependencyDetectedException;
import repo.exception.ItemAlreadyExistsException;
import service.ServiceFriendship;
import service.ServiceUser;
import util.valid.NameValidator;
import util.valid.exception.InvalidNameException;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Optional;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String url = "jdbc:postgresql://localhost:5432/social";
        String userName = "postgres";
        String password = "";

        NameValidator nameValidator = new NameValidator();

        // REPO
        RepoUser repoUser = new RepoUserDB(url, userName, password);
        RepoFriendship repoFriendship = new RepoFriendshipDB(url, userName, password);

        // SERVICE
        ServiceUser serviceUser = new ServiceUser(repoUser, repoFriendship);
        ServiceFriendship serviceFriendship = new ServiceFriendship(repoUser, repoFriendship);

        Scanner scanner = new Scanner(System.in);
        while (true) {
            // MENU
            String[] actions = {"user add", "user remove", "user list", "friendship add", "friendship remove", "friendship list", "community count", "community mostsociable"};
            System.out.println("Actions: ");
            for (String action : actions) {
                System.out.println("- " + action);
            }
            System.out.print("> ");

            if (!scanner.hasNextLine()) break;
            String action = scanner.nextLine().strip();
            if (action.isEmpty()) continue;

            try {
                /*--*/ if (action.equals("user add")) {
                    String name = TUI.textPrompt(scanner, "name", line -> line, nameValidator);
                    serviceUser.addUser(name);
                } else if (action.equals("user remove")) {
                    Optional<User> user = TUI.userByNamePrompt(serviceUser, scanner);
                    if (user.isPresent()) {
                        serviceUser.removeUser(user.get().getId());
                    }
                } else if (action.equals("user list")) {
                    User[] users = serviceUser.getUsers();
                    for (User user : users) {
                        System.out.println(user);
                    }
                } else if (action.equals("friendship add")) {
                    Optional<User> user1 = TUI.userByNamePrompt(serviceUser, scanner);
                    if (user1.isPresent()) {
                        Optional<User> user2 = TUI.userByNamePrompt(serviceUser, scanner);
                        if (user2.isPresent()) {
                            serviceFriendship.addFriendship(user1.get().getId(), user2.get().getId());
                        }
                    }
                } else if (action.equals("friendship remove")) {
                    Optional<User> user1 = TUI.userByNamePrompt(serviceUser, scanner);
                    if (user1.isPresent()) {
                        Optional<User> user2 = TUI.userByNamePrompt(serviceUser, scanner);
                        if (user2.isPresent()) {
                            serviceFriendship.removeFriendship(user1.get().getId(), user2.get().getId());
                        }
                    }
                } else if (action.equals("friendship list")) {
                    Friendship[] friendships = serviceFriendship.getFriendships();
                    for (Friendship friendship : friendships) {
                        User user1 = serviceUser.findById(friendship.getId().getFirstUserId());
                        User user2 = serviceUser.findById(friendship.getId().getSecondUserId());
                        LocalDateTime friendsSince = friendship.getFriendsSince();
                        System.out.println(user1.getName() + " -> " + user2.getName() + " (" + friendsSince.format(Friendship.DATE_TIME_FORMATTER) + ")");
                    }
                } else if (action.equals("community count")) {
                    int count = serviceFriendship.getCommunitiesCount();
                    System.out.println(count);
                } else if (action.equals("community mostsocial")) {
                    ArrayList<User> community = serviceFriendship.getMostSociableCommunity();
                    System.out.println("Most sociable community is:");
                    for (User user : community) {
                        System.out.println(user);
                    }
                }
            } catch (ItemAlreadyExistsException ex) {
                System.err.println("Item already exists!");
            } catch (ItemDoesntExistException ex) {
                System.err.println("Item doesn't exist!");
            } catch (DependencyDetectedException ex) {
                System.err.println("Can't delete user, because user still has friendships!");
            } catch (InvalidNameException ex) {
                System.err.println("Invalid user name!");
            }
        }
    }
}
