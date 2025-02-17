let scrollSpeed = 500;
let scrolling = false;

function startScrolling(direction) {
  const projectsContainer = document.querySelector('.Projects');
  function scrollStep() {
    if (!scrolling) return;
    projectsContainer.scrollBy({ left: direction * scrollSpeed, behavior: 'auto' });
    ;
  }
  scrollStep();
}

document.getElementById('scrollLeftBtn').addEventListener('mouseover', () => {
  scrolling = true;
  startScrolling(-1);
});

document.getElementById('scrollRightBtn').addEventListener('mouseover', () => {
  scrolling = true;
  startScrolling(1);
});

document.getElementById('scrollLeftBtn').addEventListener('mouseout', () => {
  scrolling = false;
});

document.getElementById('scrollRightBtn').addEventListener('mouseout', () => {
  scrolling = false;
});

document.getElementById('scrollLeftBtn').addEventListener('click', () => {
    scrolling = true;
    startScrolling(-1);
  });

  document.getElementById('scrollRightBtn').addEventListener('click', () => {
    scrolling = true;
    startScrolling(1);
  });