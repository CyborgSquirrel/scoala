public class Government {
    private Government() {

    }

    private static Government lazyInstance = null;
    public static Government getLazyInstance() {
        if (lazyInstance == null) {
            lazyInstance = new Government();
        }
        return lazyInstance;
    }

    private static Government eagerInstance = new Government();
    public static Government getEagerInstance() {
        return eagerInstance;
    }
}
