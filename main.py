# test vars. get it from file
lane = 4
green = [15, 35, 25, 25]
red = [None] * lane
count = [None] * lane
value = [45, 56, 12, 199]
traffic_rate = 2.0
chance = [None] * lane
max_threshold = 50
base_increment = 5
won = False


def init():
    default_time()
    reset_chance()


def calc_red():
    # never call this directly.
    for x in range(lane):
        temp = 0
        for y in range(x, x + (lane - 1)):
            temp += green[(y + 1) % lane]
        red[x] = temp


def default_time():

    calc_red()
    return red


def reset_chance():
    won = False
    for x in range(lane):
        chance[x] = -1


def get_count():
    # we need files
    for x in range(lane):
        count[x] = value[x]


def compare():
    index = 0
    # use dictionary or something because index may mess up
    max_count = max(count)
    for x in range(lane):
        if(max_count == count[x]):
            index = x
    return index, max_count


def increment():
    global won
    temp = compare()
    lane_no = temp[0]
    num_vehicles = temp[1]
    temp = (1 / traffic_rate) * num_vehicles + base_increment

    if (temp > max_threshold):
        temp = max_threshold

    if (temp < base_increment):
        temp = base_increment

    temp = int(round(temp))

    if ((chance[lane_no] == 1) & (won == False)):
        print("twice")
        count[lane_no] = -1
        won = True
        increment()

    else:
        # update time logic should be over here
        print('' + str(lane_no) + " needs " +
              str(temp) + " time.", chance, count)
        chance[lane_no] += 1
        if(won == True):
            count[lane_no] = -1
            if (min(chance) == 0):
                reset_chance()
                get_count()


init()
get_count()
increment()
value = [56, 67, 24, 50]
get_count()
increment()
increment()
increment()
increment()
increment()
increment()
increment()
increment()
increment()
increment()
increment()
increment()
