# Mobile Architect & Programming

## What user needs the app was designed to address

For context, the app I designed was an event tracker that allows users to log in and register an account, and create events with text and an associated date and time.  The end goal was for this to be a functioning event tracker which would notify users when an event came up, with a multi-user system so that events are safe and secure.

## What screens and features were necessary to support user needs and product a user-centered UI for the app

Keeping the screens simple was a top priority for me.  To meet user needs, I had to create a screen to log in/register, the main screen to list events and a couple buttons, a manage notifications screen to request SMS permission, and a manage event screen which would act as the add and edit screen.  There is also a dummy screen only used to refresh the RecyclerView dataset when returned from, such as when deleting an event. I did not know of any other clean way to do it from inside an Adapter's ViewHolder.

## How I approached the process of coding the app

Taking it screen-by-screen to keep my thought processes narrowed down was critical in getting the entire app written in half a day.  Looking up basic issues and tutorials also helped, because I now know of a good way to approach designing and developing my application without getting so hung up on the details.

## How I test to ensure my code is functional

Having the app running in the emulator at all times helps, as well as refreshing the activity when smaller changes are made.  Sometimes changes would require restarting the activity altogether, but having the application running on the side definitely helped visualize and keep the end goal at the top of my head.  Following good tutorials and ensuring there are no errors in the IDE helped tremendously.

## Where I had to innovate to overcome a challenge

I had to create a dummy screen with nothing in it to act as a "refresh" event for the RecyclerView when an event is deleted.  I can feel that it isn't the proper way to go about deleting a RecyclerView item and refreshing, but it worked without any flaws, so I kept it as-is.  If I had the time to revisit the way the app was designed, I would look into examples of how other people do the same abstract idea of refreshing a RecyclerView's dataset from inside an Adapter's ViewHolder.

## What specific component I was particularly successful in demonstrating my knowledge, skills, and experience

Nothing.



Kidding, I feel like the way I handled the login process was particularly clean, as well as going from the main screen to the manage event screen.  I believe other students may have had a couple different screens to add and edit an event, but I was able to narrow it down to a single manage screen, which I am proud of.

I believe my experience of development shows in the way I lay out my code cleanly and comment where I feel is necessary, though I *did* have points docked off for not commenting enough.  I thought it was self-documenting! ;(

